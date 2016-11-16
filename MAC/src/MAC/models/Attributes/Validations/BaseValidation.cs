using System;
using MAC.Types;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.Models.Attributes.Validations
{
    /// <summary>
    /// Base atttrbiute that all validations should be derivted from
    /// </summary>
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property | AttributeTargets.Parameter,
        AllowMultiple = false)]
    public abstract class BaseValidation : Attribute
    {
        /// <summary>
        /// Validate a given object
        /// </summary>
        /// <param name="o">object to validate</param>
        /// <returns>
        /// <c>false</c> if the object is not valid
        /// <c>true</c> if the object is valid
        /// </returns>
        public abstract bool IsValid(BaseType o);
    }
}
