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
           auto created_scope =
               ioc::core::Resolve<Scope>("IoC.Scope.Create.Empty");
           auto parent_scope = [&]() {
             if (args.size() > 0) return std::any_cast<Scope>(args[0]);
             return ioc::core::Resolve<Scope>("IoC.Scope.Current");
           }();
           created_scope->insert(
               {"IoC.Scope.Parent",
                [parent_scope](ArgsVec args) { return parent_scope; }});
           return created_scope;
         }});
    root_scope_->insert({"IoC.Register", [](ArgsVec args) {
                           return MakeCommand<RegisterDependency>(
                               std::any_cast<std::string>(args[0]),
                               std::any_cast<IocFunctor>(args[1]));
                         }});
    ioc::core::Resolve<CommandPtr>(
        "Update Ioc Dependency Strategy", {[](ioc::IocStrategy old_strategy) {
          return [&](std::string dependency, ArgsVec args) {
            auto scope = current_scope_ ? current_scope_ : root_scope_;
            DependencyResolver dependency_resolver{scope};
            return dependency_resolver.Resolve(dependency, args);
          };
        }})
        ->Execute();
    already_successfully_ = true;
  }
}
}  // namespace ioc
