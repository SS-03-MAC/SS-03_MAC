using System;
using System.Runtime.Serialization;


namespace MAC.Types
{
    /// <summary>
    /// Stores and vaildates dates
    /// Stored as a SQL date
    /// eg 08/28/2016
    /// 
    /// Stroed in C# as a System.DateTime object at time 00:00
    /// </summary>
    public class Date : BaseType<Date, System.DateTime>
    {
        /// <summary>
        /// Data that is stored in the type represented in as System.DateTime
        /// </summary>
        private System.DateTime Data;

        /// <summary>
        /// Initializes a Date from a System.DateTime object
        /// </summary>
        /// <param name="input">the DateTime to be stored</param>
        public Date(System.DateTime input)
        {
            Data = input.Date;
            DatabaseFieldType = DatabaseFieldTypes.time;
        }

        /// <summary>
        /// Default constructor
        /// </summary>
        public Date()
        {

        }

        /// <summary>
        /// Initializes a Date from SerializationInfo
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public Date(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            Data = ((System.DateTime)info.GetValue("Data", typeof(System.DateTime))).Date;
            DatabaseFieldType = DatabaseFieldTypes.time;
        }

        /// <summary>
        /// This will check for:
        /// Will check if the time is format can interpered as a datetime
        /// </summary>
        /// <returns>If the Date stored is valid</returns>
        public override bool Validate()
        {
            return Data != null;
        }

        /// <summary>
        /// Compare the time
        /// </summary>
        /// <param name="other">the BaseType object to compare with</param>
        /// <returns>the result of comparing System.DateTime</returns>
        public override int CompareTo(object other)
        {
            if (other is Date)
            {
                return Data.CompareTo(((Date)other).Data);
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the time
        /// </summary>
        /// <param name="other">The BaseType object to check equality with</param>
        /// <returns>True if equal, False otherwise</returns>
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
        /// Serializes the DateTime
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
        public override System.DateTime Value
        {
            get { return Data; }
            set { Data = value; }
        }

        /// <summary>
        /// Return the data as string
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
    }
}