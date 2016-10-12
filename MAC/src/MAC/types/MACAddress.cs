using System;
using System.Runtime.Serialization;


namespace MAC.Types.Internet
{
    /// <summary>
    /// Stores and vaildates MAC Adresses
    /// Stored as SQL type varchar
    /// </summary>
    public class MACAddress : BaseType
    {
        static string validHex = "0123456789ABCDEFabcdef";
        private string data;
        private long addressValue;
        private bool valid;
        
        public MACAddress(string input)
        {
            data = input.Trim();
            valid = Validate();
            if (valid)
            {
                addressValue = GetNumericalAddress(data);
            }
        }

        public MACAddress(SerializationInfo info, StreamingContext context)
        {
            if(info == null)
            {
                throw new ArgumentNullException("info");
            }
            data = (string)info.GetValue("data", typeof(string));
            data = data.Trim();
            valid = Validate();
            if (valid)
            {
                addressValue = GetNumericalAddress(data);
            }
        }

        /// <summary>
        /// takes in a string of a mac adress and converts it to a numeric value
        /// we do this by stripping out any seperators, then parsing the resulting
        /// hex value. This allows us a way to better compare MAC Addresses
        /// 
        /// </summary>
        /// <param name="data">the mac address to be parsed</param>
        /// <returns>the numerical value represented by the MAC address</returns>
        private long GetNumericalAddress(string data)
        {
            string hex = data.Replace(".", "").Replace("-", "").Replace(":", "");
            return Int64.Parse(hex.ToLower(), System.Globalization.NumberStyles.HexNumber);
        }

        /// <summary>
        /// This will check if is a MAC Address. We accept three standard formats:
        /// 1.) XXX.XXX.XXX.XXX
        /// 2.) XX-XX-XX-XX-XX-XX
        /// 3.) XX:XX:XX:XX:XX:XX
        /// Where each X represents a valid hex character. We accept both upper- 
        /// lower- and mixed- case hexecdecimal values. 
        /// </summary>
        /// <returns>weather the string stored in data is a vaid MAC address</returns>
        public override bool Validate()
        {
            int hexValues = 0;
            int colons = 0;
            int dashes = 0;
            int dots = 0;

            for(int i = 0; i < data.Length; i++)
            {
                if (validHex.Contains(data[i]+""))
                {
                    hexValues++;
                }
                if(data[i] == '.')
                {
                    //if it has dots, it just be in format XXX.XXX.XXX.XXX
                    if (i % 4 != 3) 
                    {
                        return false;
                    }
                    dots++;
                }
                if (data[i] == '-')
                {
                    //if it has dots, it just be in format XX-XX-XX-XX-XX-XX
                    if (i % 3 != 2)
                    {
                        return false;
                    }
                    dashes++;
                }
                if (data[i] == ':')
                {
                    //if it has dots, it just be in format XX:XX:XX:XX:XX:XXX
                    if (i % 3 != 2)
                    {
                        return false;
                    }
                    colons++;
                }
            }

            return (hexValues == 12) && ((dots == 3 && dashes == 0 && colons == 0)
                || (dots == 0 && dashes == 5 && colons == 0) 
                || (dots == 0 && dashes == 0 && colons == 5));
        }

        /// <summary>
        /// Compare the MAC Address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other)
        {
            if(other is MACAddress)
            {
                if (!((MACAddress)other).valid)
                {
                    throw new ArgumentException("This is not a valid MAC Address");
                }
                return this.addressValue.CompareTo(((MACAddress)other).addressValue);
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the MAC Address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other)
        {
            try
            {
                return this.addressValue == ((MACAddress)other).addressValue;
            }
            catch (Exception)
            {
                return false;
            }
        }

        /// <summary>
        /// Should return a string of the MAC Address
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            if(info == null)
            {
                throw new ArgumentNullException("info");
            }
            info.AddValue("data", data);
        }

        /// <summary>
        /// Returns the stored as a string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return data;
        }

        public string Value
        {
            get { return data; }
            set
            {
                data = value;
                valid = Validate();
                if (valid)
                {
                    addressValue = GetNumericalAddress(data);
                }
            }
        }
    }
}