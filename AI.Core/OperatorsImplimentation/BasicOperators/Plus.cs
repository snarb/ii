﻿namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class Plus : Operator
    {
        public Plus(Entity thisEntity)
            : base(thisEntity)
        {
            EnterContactsCount = 2;
        }

        public override void Action()
        {
            var value = EnterContacts[0].Value + EnterContacts[1].Value;
            ExitContacts.SetValue(value);
        }
    }
}