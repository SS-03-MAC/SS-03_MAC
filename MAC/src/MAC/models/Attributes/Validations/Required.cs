using MAC.Types;
using System;

namespace MAC.Models.Attributes.Validations
{
    /// <summary>
    /// Marks a field as required
    /// </summary>
    public class RequiredField : BaseValidation
    {

        /// <summary>
        /// Allow empty strings
        /// </summary>
        public bool AllowEmptyString { get; set; }

        /// <summary>
        /// Override of <see cref="BaseValidation.IsValid(object)"/> 
        /// Underline check uses <see cref="System.ComponentModel.DataAnnotations.RequiredAttribute"/>.
        /// </summary>
        /// <param name="o">object to check</param>
        /// <returns>
        /// <c>false</c> If empty 
        /// <c>true</c> If defined
        /// </returns>
        public override bool IsValid(BaseType o)
        {
            if (o == null)
            {
                return false;
            }
            var attr = new System.ComponentModel.DataAnnotations.RequiredAttribute();
            return attr.IsValid(o.GetRawObject());
        }
    }
}
