using System;

namespace MAC.Models
{
    /// <summary>
    /// Used in places where something is given garage if expection is called
    /// </summary>
    public class UnexpectedResultExpection : Exception
    {
        public UnexpectedResultExpection() : base() { }
        public UnexpectedResultExpection(string message) : base(message) { }
        public UnexpectedResultExpection(string message, Exception e) : base(message, e) { }
    }
}
