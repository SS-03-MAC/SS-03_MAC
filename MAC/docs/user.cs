using System;
using System.Collections;

/// <summary>
///   This is an example model class.
///   I have subbed out the methods that will created in this file by the automatic system.
/// </summary> 
public class User {
  public long Id {get;}
  public string Email {get; set;}
  /// <summary>
  /// On set will set PasswordDigest to the BCrypt Password
  /// </summary>
  public virtual strng Password {get; set;}
  public string PasswordDigest {get; set;}

  public User Get(long id) {
    // SELECT
  }

  public List<Users> GetAll() {
    // SELECT
  }

  public bool Save() {
    if (Id == null) {
      // INSERT
      // Validate
      // If Valid will update Id on model
    } else {
      // Valid
      // UPDATE
    }
  }

  public bool Delete() {
    // DELETE
  }

  public List<string> Valid() {
    // Runs Validations
    // Returns if all vaildtions passed
    // Add errors to the list
  }
}
