using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

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
