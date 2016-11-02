using System;
using System.Runtime.Serialization;


namespace MAC.Types
{
    /// <summary>
    /// Stores and vaildates times
    /// Stored as a SQL time
    /// eg 08/28/2016
    /// </summary>
    public class Time : BaseType<Time, TimeSpan>
    {
        private TimeSpan Data;

        /// <summary>
        /// initialized a Time from a TimeSpan object
        /// </summary>
        /// <param name="input">the TimeSpan to be stored</param>
        public Time(TimeSpan input)
        {
            Data = input;
            DatabaseFieldType = DatabaseFieldTypes.time;
        }

        /// <summary>
        /// initializes a Time from SerializationInfo
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public Time(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            Data = (TimeSpan)info.GetValue("Data", typeof(TimeSpan));
        }

        /// <summary>
        /// This will check for:
        /// Will check if the time is format can interpered as a time
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            return Data != null;
        }

        /// <summary>
        /// Compare the time
        /// </summary>
        /// <param name="other">the BaseType object to compare with</param>
        /// <returns>the result of TimeSpan.CompareTo()</returns>
        public override int CompareTo(object other)
        {
            if (other is Time)
            {
                return Data.CompareTo(((Time)other).Data);
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the time
        /// </summary>
        /// <param name="other">The BaseType object to check equalitry with</param>
        /// <returns>True if equals, false otherwise</returns>
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

        /// <summary>
        /// Serializes the Time
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
        /// Direct access to the stored value
        /// </summary>
        public override TimeSpan Value
        {
            get { return Data; }
            set { Data = value; }
        }

        /// <summary>
        /// Returns the data stored as a string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Data.ToString();
        }

        public override object GetRawObject()
        {
            return Data as object;
        }
    }
}