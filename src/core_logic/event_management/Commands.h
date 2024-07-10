//
// Created by Josi on 07.06.2024.
//

#ifndef HIVE_COMMANDS_H
#define HIVE_COMMANDS_H

namespace CoreLogic::EventManagement
{

    class Command
    {
        public:
            virtual void execute() = 0;
    };

    namespace InGameCommand
    {
        class MoveDownCommand : public Command
        {
            public:
                void execute() override;
        };

        class MoveUpCommand : public Command
        {
            public:
                void execute() override;
        };

        class MoveLeftCommand : public Command
        {
            public:
                void execute() override;
        };

        class MoveRightCommand : public Command
        {
            public:
                void execute() override;
        };



        class ActionCommand : public Command
        {
            public:
                void execute() override;
        };

        class DeathAbilityCommand : public Command
        {
            public:
                void execute() override;
        };

        class DisconnectCommand : public Command
        {
            public:
                void execute() override;
        };

        class InteractCommand : public Command
        {
            public:
                void execute() override;
        };

        class HighlightInteractablesCommand : public Command
        {
            public:
                void execute() override;
        };

        class PauseCommand : public Command
        {
            public:
                void execute() override;
        };

    }

    namespace MenuCommand
    {
        class CursorDownCommand : public Command
        {
            public:
                void execute() override;
        };

        class CursorUpCommand : public Command
        {
            public:
                void execute() override;
        };

        class CursorLeftCommand : public Command
        {
            public:
                void execute() override;
        };

        class CursorRightCommand : public Command
        {
            public:
                void execute() override;
        };

        class BackCommand : public Command
        {
            public:
                void execute() override;
        };

        class SelectCommand : public Command
        {
            public:
                void execute() override;
        };
    }
}


#endif //HIVE_COMMANDS_H
