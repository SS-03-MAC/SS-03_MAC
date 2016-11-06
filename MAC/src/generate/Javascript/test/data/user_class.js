var User = function(Password, FullName, City){
  this.Password = Password;
  this.FullName = FullName;
  this.City = City;
  this.id = 0;
  this.CreatedAt = Date.now();
  this.UpdatedAt = Date.now();

  this.save = function(){
    var xhr = new XMLHttpRequest();
    if(id == 0){
      xhr.open("POST", "/users/", true);
    } else{
      xhr.open("POST", "/users/"+id);
    }

    xhr.setRequestHeader("Content-type", "application/json");

    xhr.onreadystatechange = function(){
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          alert(xhr.responseText);
        } else{
          throw new Error(xhr.statusText);
        }
      }
    };

    var data = JSON.serialize(this);
    xhr.send(data);
  };

  this.delete = function(){
    if(id == 0){
      return; //never saved to database, don't have to do anything
    }

    var xhr = new XMLHttpRequest();
    xhr.setRequestHeader("Content-type", "application/json");
    xhr.onreadystatechange = function() {
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          alert(xhr.responseText);
        } else{
          throw new Error(xhr.statusText);
        }
      }
    };

    xhr.open("DELETE", "/users/"+id, true);
    xhr.send(null);
  };
};

User.get = function(id, ret){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["id", "CreatedAt", "UpdatedAt", "Password", "FullName", "City"];
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

  xhr.open("GET", "/users/"+id, true);
  xhr.send(null);
};

User.getAll = function(arr){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["id", "CreatedAt", "UpdatedAt", "Password", "FullName", "City"];
        var result = JSON.parse(xhr.responseText);
        
        for(var i = 0; i < result.length; i++){
          tmp = new User();
          obj = result[i];
          for(var field in obj){
            if(fields.indexOf(field) !== -1){
              tmp[field] = obj[field];
            }
          }

          arr.push(tmp);
        }
      } else{
        throw new Error(xhr.statusText);
      }
    }
  };

  xhr.open("GET", "/users.json", true);
  xhr.send(null);
};
