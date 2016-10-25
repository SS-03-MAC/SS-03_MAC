using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.Models
{
    /// <summary>
    /// This expection will be throw if the record is valid and record is try 
    /// to be saved, etc.
    /// </summary>
    public class RecordNotValidException : Exception
    {
        public RecordNotValidException() : base() { }
        public RecordNotValidException(string message) : base(message) { }
        public RecordNotValidException(string message, Exception e) : base(message, e) { }
    }
}
