#include "Entry.h"

#include <ll/api/memory/Hook.h>
#include <ll/api/mod/RegisterHelper.h>
#include <mc/world/level/LevelSettings.h>

// Hook LevelSettings 的成就禁用判断，直接返回 false（永不禁用成就）
LL_AUTO_TYPE_INSTANCE_HOOK(
    LevelSettingsHook,
    ll::memory::HookPriority::Normal,
    LevelSettings,
    &LevelSettings::achievementsWillBeDisabledOnLoad,
    bool
) {
    const auto& logger = mfa::MForceAchievements::getInstance().getSelf().getLogger();
    logger.info("已拦截成就禁用检测，强制保持成就开启！");
    return false;
}

namespace mfa
{

MForceAchievements& MForceAchievements::getInstance()
{
    static MForceAchievements instance;
    return instance;
}

bool MForceAchievements::load() const
{
    const auto& logger = getSelf().getLogger();
    logger.debug("Loading...");
    return true;
}

bool MForceAchievements::enable() const
{
    const auto& logger = getSelf().getLogger();
    logger.debug("Starting up...");
    return true;
}

bool MForceAchievements::disable() const
{
    const auto& logger = getSelf().getLogger();
    logger.debug("Shutting down...");
    return true;
}

} // namespace mfa

LL_REGISTER_MOD(mfa::MForceAchievements, mfa::MForceAchievements::getInstance());