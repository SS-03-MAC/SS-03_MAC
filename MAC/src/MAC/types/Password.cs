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
     public bool Validate() {
       return false;
     }

     /// <summary>
     /// Compare the hashes
     /// </summary>
     /// <param name="other"></param>
     /// <returns></returns>
     public int CompareTo(BaseType other) {
       return 0;
     }

     /// <summary>
     /// Returns the hashed password
     /// </summary>
     /// <returns></returns>
     public string ToString() {
       return "";
     }

     /// <summary>
     /// Check the password hashes for equity
     /// </summary>
     /// <param name="other"></param>
     /// <returns></returns>
     public int Equals(BaseType other) {
       return 0;
     }
   }
 }
