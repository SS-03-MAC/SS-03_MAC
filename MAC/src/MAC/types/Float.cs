using System;
using System.Runtime.Serialization;


namespace MAC.Types
{
    /// <summary>
    /// Stores and vaildates Floats
    /// Stored as SQL type float
    /// </summary>
    public class Float : BaseType
    {
        /// <summary>
        /// This will check if is a float
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare the float
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks equality of the float
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return the float
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            throw new NotImplementedException();
        }
    }
}
