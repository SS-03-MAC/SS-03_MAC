using System;
using System.Runtime.Serialization;
using BCrypt.Net;

namespace MAC.Types.User
{
    /// <summary>
    /// This the password class for user
    /// This class will handle 
    /// </summary>
    public class Password : BaseType
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

        public Password(string password)
        {
            Data = HashPassword(password);
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
            return Data;
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
    }
}
