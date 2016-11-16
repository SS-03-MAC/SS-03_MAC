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
        /// </summary>
        /// <param name="o"></param>
        /// <returns></returns>
        public override bool IsValid(object o)
        {
            if (o is MAC.Types.String)
            {
                MAC.Types.String a = (MAC.Types.String) o;
                o = a.Value as object;
            }

            var attr = new System.ComponentModel.DataAnnotations.RequiredAttribute();
            return attr.IsValid(o);
        }
    }
}
