#include <mods/CommandSupport.h>

#include "settings.h"

bool disable_temporary = false;

class AuditCommand : public Command {
public:
  enum class Mode { Disable, Enable } mode;
  bool set_mode;

  void execute(CommandOrigin const &origin, CommandOutput &output) {
    if (set_mode) { disable_temporary = mode == Mode::Disable; }
    output.success("commands.audit.success", {disable_temporary ? "off" : "on"});
  }
  static void setup(CommandRegistry *registry) {
    using namespace commands;
    registry->registerCommand(
        "audit", "commands.audit.description", CommandPermissionLevel::GameMasters, CommandFlagCheat, CommandFlagNone);
    addEnum<Mode>(registry, "audit-mode", {{"off", Mode::Disable}, {"on", Mode::Enable}});
    registry->registerOverload<AuditCommand>(
        "audit",
        optional<CommandParameterDataType::ENUM>(&AuditCommand::mode, "mode", "audit-mode", &AuditCommand::set_mode));
  }
};

void InitCommand(CommandRegistry *registry) { AuditCommand::setup(registry); }