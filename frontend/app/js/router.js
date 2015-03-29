define([ "backbone", "views/index", "views/widget"], 
function(Backbone, IndexView, Widget) {
	var AppRouter = Backbone.Router.extend({
		routes : {
			'widgetlist' : 'widgetlist',
			'widgetget/:type/:key' : 'widgetget',
			'*actions' : 'defaultAction',
		}
	});
	var initialize = function() {
		var router = new AppRouter();
		
		router.on('route:defaultAction', function() {
			new IndexView();
		});
		
		router.on('route:widgetlist', function() {
			new Widget();
		});
		
		router.on('route:widgetget', function(type, key) {
			new WidgetGet(type, key);
		});
		
		Backbone.history.start();
	};
	return {
		initialize : initialize
	};
});