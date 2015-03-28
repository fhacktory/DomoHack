define([ "backbone", "service" ], 
function(Backbone, Service) {
	var ServiceList = Backbone.Collection.extend({
		model: Service,
		//url: 'http://localhost:5000/rest/list',
		url: "http://localhost/test.json",
		parse: function(response) {
            return response.results;
        },
        sync: function(method, model, options) {
            var params = _.extend({
                type: 'GET',
                dataType: 'jsonp',
                url: this.url,
                processData: false
            }, options);

            return $.ajax(params);
        }
        
	});
	return ServiceList;
});