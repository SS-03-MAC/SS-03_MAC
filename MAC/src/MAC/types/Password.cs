using System;
using System.Runtime.Serialization;
using System.Security.Cryptography;

namespace MAC.Types.User
{
    /// <summary>
    /// This the password class for user
    /// This class will handle 
    /// </summary>
    public class Password : BaseType
    {
        private string data;
        /// <summary>
        /// Validates the password with the following requirements:
        /// - 8 or 10 chars
        /// - Not blank
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            throw new NotImplementedException();
        }

        public Password(string password)
        {

        }

        /// <summary>
        /// Compares the hashes
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Returns the hashed password
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Check the password hashes for equity
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should a password be Serializatiable?
        /// </summary>
        /// <returns></returns>
        public override void GetObjectData(SerializationInfo info, StreamingContext cont)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// This method hashes the password
        /// </summary>
        /// <param name="PlainTextPassword"></param>
        /// <returns></returns>
        private string HashPassword(string PlainTextPassword)
        {
            return null;
        }
    }
}
