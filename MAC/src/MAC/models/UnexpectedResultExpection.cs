using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.Models
{
    public class UnexpectedResultExpection : Exception
    {
        public UnexpectedResultExpection() : base() { }
        public UnexpectedResultExpection(string message) : base(message) { }
        public UnexpectedResultExpection(string message, Exception e) : base(message, e) { }
    }
}
