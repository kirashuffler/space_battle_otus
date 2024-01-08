#include "../include/IoC/Init.hpp"

#include "../include/IoC/ClearCurrentScope.hpp"
#include "../include/IoC/DependencyResolver.hpp"
#include "../include/IoC/RegisterDependency.hpp"
#include "../include/IoC/SetCurrentScope.hpp"

namespace ioc {
void Init::Execute() {
  if (already_successfully_) {
    return;
  }
  {
    std::lock_guard<std::mutex> l(root_scope_mtx_);

    root_scope_->insert({"IoC.Scope.Current.Set", [](ArgsVec args) {
                           return MakeCommand<SetCurrentScope>(args[0]);
                         }});
    root_scope_->insert({"IoC.Scope.Current.Clear", [](ArgsVec args) {
                           return MakeCommand<ClearCurrentScope>();
                         }});
    root_scope_->insert({"IoC.Scope.Current", [](ArgsVec args) {
                           if (current_scope_) return current_scope_;
                           return root_scope_;
                         }});
    root_scope_->insert({"IoC.Scope.Parent", [](ArgsVec args) {
                           throw std::runtime_error(
                               "The root scope has no parent scope.");
                           return std::any{};
                         }});
    root_scope_->insert({"IoC.Scope.Create.Empty", [](ArgsVec args) {
                           return std::make_shared<DependenciesMap>();
                         }});
    root_scope_->insert(
        {"IoC.Scope.Create", [](ArgsVec args) {
           auto created_scope = ioc::Resolve<Scope>("IoC.Scope.Create.Empty");
           auto parent_scope = [=]() {
             if (args.size() > 0) return std::any_cast<Scope>(args[0]);
             return ioc::Resolve<Scope>("IoC.Scope.Current");
           }();
           created_scope->insert({"IoC.Scope.Parent",
                                  [=](ArgsVec args) { return parent_scope; }});
           return created_scope;
         }});
    root_scope_->insert({"IoC.Register", [](ArgsVec args) {
                           auto dependency = [&]() -> std::string {
                             try {
                               return std::any_cast<const char*>(args[0]);
                             } catch (std::bad_cast& e) {
                             };
                             return std::any_cast<std::string>(args[0]);
                           }();
                           auto functor = std::any_cast<IocFunctor>(args[1]);
                           return MakeCommand<RegisterDependency>(dependency,
                                                                  functor);
                         }});
    ioc::IocStrategyUpdater updater =
        [](ioc::IocStrategy old_strategy) -> ioc::IocStrategy {
      return [&](std::string dependency, ArgsVec args) -> std::any {
        auto scope = current_scope_ != nullptr ? current_scope_ : root_scope_;
        DependencyResolver dependency_resolver{scope};
        return dependency_resolver.Resolve(dependency, args);
      };
    };
    ioc::Resolve<CommandPtr>("Update Ioc Resolve Dependency Strategy",
                             {updater})
        ->Execute();
    already_successfully_ = true;
  }
}
}  // namespace ioc
