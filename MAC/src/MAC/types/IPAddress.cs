using System;
using System.Runtime.Serialization;


namespace MAC.Types.Internet
{
    /// <summary>
    /// Stores and vaildates IP Address
    /// </summary>
    public class Address : BaseType
    {
        /// <summary>
        /// This will check for:
        /// If the address is vaildate
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks equality of the address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return the address as a string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks if the stored address is IPv4
        /// </summary>
        /// <returns>true if the address resprened by the class is IPv4</returns>
        public bool IsIPv4()
        {
            return false;
        }
        
        /// <summary>
        /// Checks if the stored address is IPv6
        /// </summary>
        /// <returns>true if the address resprened by the class is IPv6</returns>
        public bool IsIPv6()
        {
            return false;
        }

        /// <summary>
        /// Returns stored data as string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            throw new NotImplementedException();
        }
    }
}