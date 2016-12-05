using System;
using System.Runtime.Serialization;


namespace MAC.Types.Internet
{
    /// <summary>
    /// Stores and vaildates URLs
    /// Stored as SQL type nvarchar
    /// </summary>
    public class Url : BaseType<Url, Uri>
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

        public Url()
        {
            DatabaseFieldType = DatabaseFieldTypes.nvarchar;
        }

        public Url(string uri)
        {
            Data = new Uri(uri);
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
        public override int CompareTo(object other)
        {
            if(other is Url)
            {
                return Data.ToString().CompareTo(((Url)other).Data.ToString());
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the URL
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(object other)
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

        public override int GetHashCode()
        {
            return base.GetHashCode();
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
        public override Uri Value
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

        /// <summary>
        /// Access to the RAW data return has a object
        /// </summary>
        /// <returns>Raw data as an object</returns>
        public override object GetRawObject()
        {
            return Data as object;
        }

        public static explicit operator string(MAC.Types.Internet.Url s)
        {
            return s.Data.OriginalString;
        }

        public static explicit operator MAC.Types.Internet.Url(string s)
        {
            return new Url(new Uri(s));
        }
    }
}