using System;
using System.Collections;
using System.Collections.Generic;

/// <summary>
///   Screensketch: Matthew Burket
///   This is an example model class.
///   I have subbed out the methods that will created in this file by the automatic system.
/// </summary>
public class User {
  /// <summary>
  /// Database id
  /// </summary>
  public long? Id { get; }
  /// <summary>
  /// A basic string field
  /// </summary>
  /// <returns></returns>
  //[Required]
  public string Email { get; set; }
  /// <summary>
  /// On set will set PasswordDigest to the BCrypt Password
  /// </summary>
  public virtual string Password { get; set; }
  /// <summary>
  /// How the Password is stored in the database
  /// </summary>
  /// <returns></returns>
  public string PasswordDigest { get; set; }
  /// <summary>
  /// Built-in field
  /// </summary>
  /// <returns></returns>
  public DateTime CreatedAt { get; set; }
  /// <summary>
  /// Built-in field
  /// </summary>
  /// <returns></returns>
  public DateTime UpdatedAt { get; }


  /// <summary>
  ///  Get a user given a Id
  /// </summary>
  /// <param name="id"></param>
  /// <returns>Users</returns>
  public static User Get(long id) {
        return null;
  }

  public static List<User> GetAll() {
        return null;
  }

    public bool Save()
    {
        if (Id == null)
        {
            // INSERT
            // Validate
            // If Valid will update Id on model
            return false;
        }
        else
        {
            // Valid
            // UPDATE
            return true;

        }
    }

  public bool Delete() {
        return false;
    // DELETE
  }

  public bool Valid() {
        return false;
    // Runs Validations
    // Returns if all vaildtions passed
  }

  public List<string> GetValidationsErrors() {
        // Gets Validation Errors
        return new List<string>();
  }
}
