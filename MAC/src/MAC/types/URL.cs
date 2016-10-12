using System;
using System.Collections.Generic;
using System.Runtime.Serialization;


namespace MAC.Types.Internet
{
    /// <summary>
    /// Stores and vaildates URLs
    /// Stored as SQL type nvarchar
    /// </summary>
    public class Url : BaseType
    {
        /// <summary>
        /// Stores the url represented by the type
        /// </summary>
        private Uri Data;
        /// <summary>
        /// This will check if is a URL
        /// </summary>
        /// <returns>If the url stored is vaild</returns>
        public override bool Validate()
        {
            if (Data == null)
            {
                return false;
            }
            return Data.IsAbsoluteUri;
        }

        public Url(Uri uri)
        {
            Data = uri;
            DatabaseFieldType = DatabaseFieldTypes.nvarchar;
        }

        public Url(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentException("Infomation was null");
            }
            Data = ((Uri)info.GetValue("Data", typeof(Uri)));
        }

        /// <summary>
        /// Compare the URL.
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other)
        {
            if(other is Url)
            {
                return this.Data.ToString().CompareTo(((Url)other).Data.ToString());
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the URL
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other)
        {
            if (other is Url)
            {
                return Data.Equals(((Url)other).Data);
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Serializes the URL
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
        /// Direct access to the URL
        /// </summary>
        public Uri Value
        {
            get { return Data; }
            set { Data = value; }
        }

        /// <summary>
        /// Return the url as a string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            if (Data != null)
            {
                return Data.ToString();
            }
            return string.Empty;
        }
    }
}