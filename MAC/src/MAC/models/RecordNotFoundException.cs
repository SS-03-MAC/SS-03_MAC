using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.Models
{
    public class RecordNotFoundException : Exception
    {
        public RecordNotFoundException() : base() { }
        public RecordNotFoundException(string message) : base(message) { }
        public RecordNotFoundException(string message, Exception e) : base(message, e) { }
    }
}
