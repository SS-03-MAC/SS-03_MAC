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
        public bool Validate()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare the MAC Address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks equality of the MAC Address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int Equals(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return a string of the MAC Address
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            throw new NotImplementedException();
        }
    }
}