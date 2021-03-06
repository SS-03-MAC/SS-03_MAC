using System;
using System.Runtime.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace MAC.Types
{
    /// <summary>
    /// Stores and vaildates Integers
    /// </summary>
    public class Integer : BaseType<Integer, int>
    {
        /// <summary>
        /// Data that is stored in the model represented in as int
        /// </summary>
        private int Data;

        /// <summary>
        /// Constructs Integer from an int type
        /// </summary>
        /// <param name="input">the int to be stored</param>
        public Integer(int input)
        {
            DatabaseFieldType = DatabaseFieldTypes.int_t;
            Data = input;
        }

        /// <summary>
        /// Default constructor
        /// </summary>
        public Integer()
        {

        }

        /// <summary>
        /// Convert int 64 to int 32
        /// </summary>
        /// <param name="data">64 bit</param>
        public Integer(long data)
        {
            DatabaseFieldType = DatabaseFieldTypes.int_t;
            Data = (int)data;
        }

        /// <summary>
        /// Set the value of Data from a string
        /// </summary>
        /// <param name="value">integer as a string</param>

        public Integer(string value)
        {
            DatabaseFieldType = DatabaseFieldTypes.int_t;
            Data = int.Parse(value);
        }


        /// <summary>
        /// Constructs Integer from SerializationInfo
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public Integer(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            DatabaseFieldType = DatabaseFieldTypes.int_t;
            Data = (int)info.GetValue("Data", typeof(int));
        }
        /// <summary>
        /// This will check for:
        /// - if is an integer
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            return true;
        }

        /// <summary>
        /// Compare the integer
        /// </summary>
        /// <param name="other">the BaseType object to compare with</param>
        /// <returns> A positive number if this > other, 0 if this == other, 
        /// and a negative number if this < other.</returns>
        public override int CompareTo(object other)
        {
            if (other is Integer)
            {
                return Data - ((Integer)(other)).Data;
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the interger
        /// </summary>
        /// <param name="other">the BaseType object to check equality with</param>
        /// <returns>true if equal. Otherwise, false</returns>
        public override bool Equals(object other)
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

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        /// <summary>
        /// Serializes the Integer
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

        /// <summary>
        /// Direct access to the data stored
        /// </summary>
        public override int Value
        {
            get { return Data; }
            set { Data = value; }
        }

        /// <summary>
        /// Return data stored as a string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Data.ToString();
        }

        /// <summary>
        /// Access to the RAW data return has a object
        /// </summary>
        /// <returns>Raw data as an object</returns>
        public override object GetRawObject()
        {
            return Data as object;
        }

        /// <summary>
        /// This is for JSON Converting
        /// </summary>
        /// <param name="l">long to cast</param>
        public static explicit operator Integer(long l)
        {
            return new Integer(l);
        }

        public static explicit operator long(Integer i)
        {
            return i.Data;
        }

        public static explicit operator Integer(int l)
        {
            return new Integer(l);
        }

        public static explicit operator int(Integer i)
        {
            return i.Data;
        }
    }
}