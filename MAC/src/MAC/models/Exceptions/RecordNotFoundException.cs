using System;

namespace MAC.Models.Exceptions
{
    public class RecordNotFoundException : Exception
    {
        public RecordNotFoundException() : base() { }
        public RecordNotFoundException(string message) : base(message) { }
        public RecordNotFoundException(string message, Exception e) : base(message, e) { }
    }
}
