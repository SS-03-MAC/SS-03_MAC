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
        /// <c>false</c> If emtpy 
        /// <c>true</c> If Defined
        /// </returns>
        public override bool IsValid(BaseType o)
        {
            var attr = new System.ComponentModel.DataAnnotations.RequiredAttribute();
            return attr.IsValid(o.GetRawObject());
        }
    }
}
