var Auth = function(token, OnwerId, user, password){
  this.Token = token;
  this.OnwerId = OnwerId;
  this.id = 0;
  this.CreatedAt = Date.now();
  this.UpdatedAt = Date.now();
  this.User = user;
  this.Password = password;

  this.save = function(path, success, failure) {
    var xhr = new XMLHttpRequest();
    if (this.id == 0) {
      xhr.open("POST", path + "/auths/", true);
    } else{
      xhr.open("PATCH", path + "/auths/"+this.id);
    }

    xhr.setRequestHeader("Content-type", "application/json");

    xhr.onreadystatechange = function(){
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          if (success !== undefined) {
            success(xhr);
          }

          console.log(xhr.responseText);
        } else{
          if (failure !== undefined) {
            failure(xhr);
          }

          throw new Error(xhr.statusText);
        }
      }
    };

    var data = JSON.stringify(this);
    xhr.send(data);
  };

  this.delete = function(path){
    if(this.id == 0){
      return; //never saved to database, don't have to do anything
    }

    var xhr = new XMLHttpRequest();
    xhr.open("DELETE", path + "/auths/"+this.id, true);
    xhr.setRequestHeader("Content-type", "application/json");
    xhr.onreadystatechange = function() {
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          console.log(xhr.responseText);
        } else{
          throw new Error(xhr.statusText);
        }
      }
    };

    xhr.send(null);
  };



};

Auth.get = function(id, ret, path){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["id", "CreatedAt", "UpdatedAt", "token", "OnwerId"];
        var result = JSON.parse(xhr.responseText);

        for(var field in result){
          if(fields.indexOf(field) !== -1){
            ret[field] = result[field];
          }
        }

      } else{
        throw new Error(xhr.statusText);
      }
    }
  };

  xhr.open("GET", path + "/auths/"+id, true);
  xhr.send(null);
};

Auth.getAll = function(arr, path, successHandler){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["id", "CreatedAt", "UpdatedAt", "token", "OnwerId"];
        var result = JSON.parse(xhr.responseText);

        for(var i = 0; i < result.length; i++){
          tmp = new Auth();
          obj = result[i];
          for(var field in obj){
            if(fields.indexOf(field) !== -1){
              tmp[field] = obj[field];
            }
          }

          arr.push(tmp);
        }

        if (successHandler !== undefined) {
          successHandler(xhr);
        }

      } else{
        throw new Error(xhr.statusText);
      }
    }
  };

  xhr.open("GET", path + "/auths.json", true);
  xhr.send(null);
};
