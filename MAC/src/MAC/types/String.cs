using System;
using System.Runtime.Serialization;


namespace MAC.Types
{
    /// <summary>
    /// Stores and vaildates strings
    /// Stored as a SQL nvarchar or varchar
    /// </summary>
    public class String : BaseType
    {
        protected string Data;

        /// <summary>
        /// Constructs String from string type
        /// </summary>
        /// <param name="input">the string to be stored</param>
        public String(string input)
        {
            Data = input;
            DatabaseFieldType = DatabaseFieldTypes.nvarchar;
        }

        /// <summary>
        /// Constructs String from SerializationInfo
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public String(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            Data = (string)info.GetValue("Data", typeof(string));
            DatabaseFieldType = DatabaseFieldTypes.nvarchar;
        }
        /// <summary>
        /// This will check for:
        /// Length with if is specified.
        /// Not sure how yet
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            return Data != null;
        }

        /// <summary>
        /// Compare the strings
        /// </summary>
        /// <param name="other">the BaseType object to compare to</param>
        /// <returns>whatever string.compareTo gives us</returns>
        public override int CompareTo(BaseType other)
        {
            if (other is String)
            {
                return this.Data.CompareTo(((String)other).Data);
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the strings
        /// </summary>
        /// <param name="other">the BaseType object to check equality with</param>
        /// <returns>true is equal, false otherwise</returns>
        public override bool Equals(BaseType other)
        {
            try
            {
                return CompareTo(other) == 0;
            }
            catch (ArgumentException)
            {
                return false;
            }
        }

        /// <summary>
        /// Serializes the string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            info.AddValue("Data", Data);
        }

        public string Value
        {
            get { return Data; }
            set { Data = value; }
        }

        public override string ToString()
        {
            return Data;
        }
    }
}