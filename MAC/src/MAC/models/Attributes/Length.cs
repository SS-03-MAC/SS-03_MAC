using System;

namespace MAC.Models.Attributes
{
    public class Length : Attribute
    {
        /// <summary>
        /// Minimim length
        /// </summary>
        public int Minimum;
        /// <summary>
        /// Maxiumim length
        /// </summary>
        public int Maximum;
    }
}
