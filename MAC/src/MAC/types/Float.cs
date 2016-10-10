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
        private double Data;

        /// <summary>
        /// Constructs a Float from a double type
        /// </summary>
        /// <param name="input">the double to be stored</param>
        public Float(double input)
        {
            Data = input;
            DatabaseFieldType = DatabaseFieldTypes.float_t;
        }

        /// <summary>
        /// Constructs a Float from SerializationInfo
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public Float(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            Data = (double)info.GetValue("Data", typeof(double));
            DatabaseFieldType = DatabaseFieldTypes.float_t;
        }

        /// <summary>
        /// This will check if is a float
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            return true;
        }

        /// <summary>
        /// Compare the float
        /// </summary>
        /// <param name="other">the BaseType to be compared to</param>
        /// <returns>a negative number if this less than other
        /// , 0 if this == other, positive if this greater than other</returns>
        public override int CompareTo(BaseType other)
        {
            if (other is Float)
            {
                return (int)(Data - ((Float)other).Data);
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the float
        /// </summary>
        /// <param name="other">the BaseType to check equality with</param>
        /// <returns>true if equal, false otherwise</returns>
        public override bool Equals(BaseType other)
        {
            try
            {
                return this.CompareTo(other) == 0;
            }
            catch (ArgumentException)
            {
                return false;
            }
        }

        /// <summary>
        /// Serializes the Float
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentException("info");
            }
            info.AddValue("Data", Data);
        }

        /// <summary>
        /// Direct access to the data stored
        /// </summary>
        public double Value
        {
            get { return Data; }
            set { Data = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Data.ToString();
        }
    }
}
