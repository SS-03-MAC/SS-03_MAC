using System;

namespace MAC.Models.Exceptions
{
    /// <summary>
    /// This expection will be returend if a record can't be found
    /// </summary>
    public class RecordNotFoundException : Exception
    {
        public RecordNotFoundException() : base() { }
        public RecordNotFoundException(string message) : base(message) { }
        public RecordNotFoundException(string message, Exception e) : base(message, e) { }
    }
}
