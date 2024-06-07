//
// Created by Josi on 07.06.2024.
//

#ifndef HIVE_COMANDS_H
#define HIVE_COMANDS_H

namespace CoreLogic::EventManagement
{

    class Comand
    {
        public:
            virtual void execute() = 0;
    };

    namespace InGameComand
    {
        class MoveDownComand : public Comand
        {
            public:
                void execute() override;
        };

        class MoveUpComand : public Comand
        {
            public:
                void execute() override;
        };

        class MoveLeftComand : public Comand
        {
            public:
                void execute() override;
        };

        class MoveRightComand : public Comand
        {
            public:
                void execute() override;
        };



        class ActionComand : public Comand
        {
            public:
                void execute() override;
        };

        class DeathAbilityComand : public Comand
        {
            public:
                void execute() override;
        };

        class DisconnectComand : public Comand
        {
            public:
                void execute() override;
        };

        class InteractComand : public Comand
        {
            public:
                void execute() override;
        };

        class HighlightInteractablesComand : public Comand
        {
            public:
                void execute() override;
        };

        class PauseComand : public Comand
        {
            public:
                void execute() override;
        };

    }

    namespace MenuComand
    {
        class CursorDownComand : public Comand
        {
            public:
                void execute() override;
        };

        class CursorUpComand : public Comand
        {
            public:
                void execute() override;
        };

        class CursorLeftComand : public Comand
        {
            public:
                void execute() override;
        };

        class CursorRightComand : public Comand
        {
            public:
                void execute() override;
        };

        class BackComand : public Comand
        {
            public:
                void execute() override;
        };

        class SelectComand : public Comand
        {
            public:
                void execute() override;
        };
    }
}


#endif //HIVE_COMANDS_H
