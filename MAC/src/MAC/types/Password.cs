using System;
using System.Runtime.Serialization;


 namespace MAC.Types.User {
   /// <summary>
   /// This the password class for user
   /// This class will handle 
   /// </summary>
   public class Password : BaseType {
     /// <summary>
     /// Validates the password with the following requirements:
     /// - 8 or 10 chars
     /// - Not blank
     /// </summary>
     /// <returns></returns>
     public override bool Validate() {
       throw new NotImplementedException();
     }

     /// <summary>
     /// Compare the hashes
     /// </summary>
     /// <param name="other"></param>
     /// <returns></returns>
     public override int CompareTo(BaseType other) {
       throw new NotImplementedException();
     }

     /// <summary>
     /// Returns the hashed password
     /// </summary>
     /// <returns></returns>
     public override string ToString() {
       throw new NotImplementedException();
     }

     /// <summary>
     /// Check the password hashes for equity
     /// </summary>
     /// <param name="other"></param>
     /// <returns></returns>
     public override bool Equals(BaseType other) {
      throw new NotImplementedException();
     }

    /// <summary>
    /// Should a password be Serializatiable?
    /// </summary>
    /// <returns></returns>
    public override void GetObjectData(SerializationInfo info, StreamingContext cont) {
      throw new NotImplementedException();
    }
   }
 }