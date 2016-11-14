﻿using System;

namespace MAC.Models.Attributes.Validations
{
    [AttributeUsage(AttributeTargets.Field|AttributeTargets.Property)]
    public class Required : Attribute
    {
        private bool required;

        public Required()
        {
            required = true;
        }

        public Required(bool required)
        {
            this.required = required;
        }
    }
}
