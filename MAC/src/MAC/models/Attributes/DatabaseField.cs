using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.Models.Attributes
{
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]
    public class DatabaseField : Attribute
    {
        private string name;
        
        public DatabaseField(string name)
        {
            this.name = name;
        }
    }
}
