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
            if (o == null)
            {
                return false;
            }

            string value = o as string;
            if (value != null && !AllowEmptyString)
            {
                return value.Trim().Length != 0;
            }

            return true;
        }
    }
}
