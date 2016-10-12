using System;
using System.Runtime.Serialization;
using System.Net;


namespace MAC.Types.Internet
{
    /// <summary>
    /// Stores and vaildates IP Address
    /// </summary>
    public class IPAddress : BaseType
    {

        private string Data;
        private bool valid;
        private System.Net.IPAddress Address;

        public IPAddress(string input)
        {
            Data = input;
            valid = Validate();
        }

        public IPAddress(SerializationInfo info, StreamingContext context)
        {
            if(info == null)
            {
                throw new ArgumentNullException("info");
            }
            Data = (string)info.GetValue("Data", typeof(string));
            valid = Validate();
        }

        /// <summary>
        /// This will check for:
        /// If the address is vaildate
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            return System.Net.IPAddress.TryParse(Data, out Address);
        }

        /// <summary>
        /// Compare address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other)
        {
            if(other is IPAddress)
            {
                if (!((IPAddress)other).valid)
                {
                    throw new ArgumentException("This is not a valid IP Address");
                }

                // System.Net.IPAddress doesn't actually have a comparison method,
                // so we need to take matters into our own hands
                byte[] bytes1 = this.Address.GetAddressBytes();
                byte[] bytes2 = ((IPAddress)other).Address.GetAddressBytes();
                int comp1 = (int)(bytes1[0] << 24 | bytes1[1] << 16 | bytes1[2] << 8 | bytes1[3]);
                int comp2 = (int)(bytes2[0] << 24 | bytes2[1] << 16 | bytes2[2] << 8 | bytes2[3]);
                return comp1.CompareTo(comp2);
            }

            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other)
        {
            try
            {
                return this.Address.Equals(((IPAddress)other).Address);
            }
            catch(Exception)
            {
                return false;
            }
        }

        /// <summary>
        /// Should return the address as a string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            if(info == null)
            {
                throw new ArgumentNullException("info");
            }
            info.AddValue("Data", Data);
        }

        /// <summary>
        /// Checks if the stored address is IPv4
        /// </summary>
        /// <returns>true if the address resprened by the class is IPv4</returns>
        public bool IsIPv4()
        {
            return Address.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork;
        }
        
        /// <summary>
        /// Checks if the stored address is IPv6
        /// </summary>
        /// <returns>true if the address resprened by the class is IPv6</returns>
        public bool IsIPv6()
        {
            return Address.AddressFamily == System.Net.Sockets.AddressFamily.InterNetworkV6;
        }

        /// <summary>
        /// Returns stored data as string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Data;
        }

        public System.Net.IPAddress Value
        {
            get { return Address; }
        }

        public bool IsValid()
        {
            return valid;
        }

    }
}