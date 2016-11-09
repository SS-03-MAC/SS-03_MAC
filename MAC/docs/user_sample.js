function bwb_user() {
    var self = this;

    this.id = 0;
    this.username = "";
    this.realname = "";
    this.email = "";
    this.deleted = false;
    this.authenticated = false;

    this.load = function(f_success, f_failure) {
        $.ajax({
            method: "GET",
            url: window.api_url + "/users/" + self.id,
            async: (f_success !== undefined || f_failure !== undefined),
            success: function(data, status, xhr) {
                var fields = ['id', 'username', 'realname', 'email', 'deleted'];
                for (var field in data) {
                    if (fields.indexOf(field) !== -1) {
                        self[field] = data[field];
                    }
                }

                if (f_success !== undefined) {
                    f_success.apply(self, [data, status, xhr]);
                }
            },
            error: function(data, status, xhr) {
                console.log("Unable to load user: " + self.id);
                if (f_failure !== undefined) {
                    f_failure.apply(self, [data, status, xhr]);
                }
            },
        });
    };

    this.create = function(pass, f_success, f_failure) {
        $.ajax({
            method: "POST",
            url: window.api_url + "/users",
            data: {
                username: self.username,
                realname: self.realname,
                password: pass,
                email: self.email
            },
            async: (f_success !== undefined || f_failure !== undefined),
            success: function(data, success, xhr) {
                self.id = data.id;
                self.authenticate(pass, f_success, f_failure);

                if (f_success !== undefined) {
                    f_success.apply(self, [data, status, xhr]);
                }
            },
            error: function(data, status, xhr) {
                if (f_failure !== undefined) {
                    f_failure.apply(self, [data, status, xhr]);
                }
            }
        });
    };

    this.save = function(f_success, f_failure) {
        $.ajax({
            method: "PUT",
            url: window.api_url + "/users/" + self.id,
            data: {
                username: self.username,
                realname: self.realname,
                email: email
            },
            async: (f_success !== undefined || f_failure !== undefined),
            success: function(data, success, xhr) {
                if (f_success !== undefined) {
                    f_success.apply(self, [data, status, xhr]);
                }
            },
            error: function(data, status, xhr) {
                if (f_failure !== undefined) {
                    f_failure.apply(self, [data, status, xhr]);
                }
            }
        });
    };

    this.delete = function(f_success, f_failure) {
        $.ajax({
            method: "DELETE",
            url: window.api_url + "/users/" + self.id,
            async: (f_success !== undefined || f_failure !== undefined),
            success: function(data, success, xhr) {
                if (f_success !== undefined) {
                    f_success.apply(self, [data, status, xhr]);
                }
            },
            error: function(data, status, xhr) {
                if (f_failure !== undefined) {
                    f_failure.apply(self, [data, status, xhr]);
                }
            }
        });
    };

    this.authenticate = function(pass, f_success, f_failure) {
        $.ajax({
            method: "POST",
            url: window.api_url + "/auth",
            data: { username: self.username, password: pass },
            async: (f_success !== undefined || f_failure !== undefined),
            success: function(data, success, xhr) {
                self.authenticated = true;
                self.id = data.owner;
                self.load(f_success, f_failure);

                if (f_success !== undefined) {
                    f_success.apply(self, [data, status, xhr]);
                }
            },
            error: function(data, status, xhr) {
                if (f_failure !== undefined) {
                    f_failure.apply(self, [data, status, xhr]);
                }
            }
        });
    };

    this.is_authenticated = function(f_success, f_failure) {
        $.ajax({
            method: "GET",
            url: window.api_url + "/auth",
            async: (f_success !== undefined || f_failure !== undefined),
            success: function(data, success, xhr) {
                self.authenticated = true;
                self.id = data.owner;
                self.load(undefined, undefined);

                if (f_success !== undefined) {
                    f_success.apply(self, [data, status, xhr]);
                }
            },
            error: function(data, status, xhr) {
                self.authenticated = false;

                if (f_failure !== undefined) {
                    f_failure.apply(self, [data, status, xhr]);
                }
            }
        });
    }

    this.logout = function(f_success, f_failure) {
        $.ajax({
            method: "DELETE",
            url: window.api_url + "/auth",
            async: (f_success !== undefined || f_failure !== undefined),
            success: function(data, success, xhr) {
                self.authenticated = false;

                if (f_success !== undefined) {
                    f_success.apply(self, [data, status, xhr]);
                }
            },
            error: function(data, status, xhr) {
                if (f_failure !== undefined) {
                    f_failure.apply(self, [data, status, xhr]);
                }
            }
        });
    };
}