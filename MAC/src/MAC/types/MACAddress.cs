using System;
using System.Runtime.Serialization;


namespace MAC.Types.Internet
{
    /// <summary>
    /// Stores and vaildates MAC Adresses
    /// Stored as SQL type varchar
    /// </summary>
    public class MACAdress : BaseType
    {
        /// <summary>
        /// This will check if is a MAC Address
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare the MAC Address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks equality of the MAC Address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return a string of the MAC Address
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Returns the stored as a string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            throw new NotImplementedException();
        }
    }
}