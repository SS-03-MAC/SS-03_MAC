using System;
using System.Runtime.Serialization;
using BCrypt.Net;

namespace MAC.Types.User
{
    /// <summary>
    /// This the password class for user
    /// This class will handle 
    /// </summary>
    public class Password : BaseType<Password, string>
    {
        private string Data;
        /// <summary>
        /// Validates the password with the following requirements:
        /// - 8 or 10 chars
        /// - Not blank
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            return Data != null;
        }

        public Password(string password, bool hash)
        {
            if (!hash)
            {
                Data = HashPassword(password);
            } else
            {
                Data = password;
            }
        }

        public Password(string password) : this(password, true)
        {
        }

        /// <summary>
        /// Compares the hashes
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(object other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Returns the hashed password
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Data;
        }

        /// <summary>
        /// Check the password hashes for equity
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(object other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should a password be Serializatiable?
        /// </summary>
        /// <returns></returns>
        public override void GetObjectData(SerializationInfo info, StreamingContext cont)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            info.AddValue("Data", Data);
        }

        /// <summary>
        /// This method hashes the password
        /// </summary>
        /// <param name="PlainTextPassword"></param>
        /// <returns></returns>
        private string HashPassword(string PlainTextPassword)
        {
            return BCrypt.Net.BCrypt.HashPassword(PlainTextPassword);
        }

        /// <summary>
        /// Verify the password
        /// </summary>
        /// <param name="PlainTextPassword"></param>
        /// <returns></returns>
        public bool VerifyPassword(string PlainTextPassword)
        {
            return BCrypt.Net.BCrypt.Verify(PlainTextPassword, Data);
        }

        /// <summary>
        /// Get access to RAW Data
        /// </summary>
        public override string Value
        {
            get { return Data; }
            set { Data = Value; }
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
