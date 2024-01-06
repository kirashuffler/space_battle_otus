#pragma once
#include <any>
#include <functional>
#include <memory>
#include <unordered_map>

namespace ioc {
using ArgsVec = std::vector<std::any>;
using IocFunctor = std::function<std::any(ArgsVec)>;
using IocStrategy = std::function<std::any(std::string, ArgsVec)>;
using IocStrategyUpdater = std::function<IocStrategy(IocStrategy)>;
using DependenciesMap = std::unordered_map<std::string, IocFunctor>;
using Scope = std::shared_ptr<DependenciesMap>;
}  // namespace ioc
