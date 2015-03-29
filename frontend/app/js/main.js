require.config({
	paths: {
		'jquery': 'libs/jquery',
		'underscore': 'libs/underscore',
		'backbone': 'libs/backbone',
		'service': 'models/service',
		'widget': 'models/widget',
		'front': 'libs/front',
		'bootstrap': 'libs/bootstrap'
	},
	shim: {
		'underscore': {
			exports: '_'
		},
		'backbone': {
			deps: ["underscore", "jquery", "front"],
			exports: 'Backbone'
		},
		'bootstrap': {
			deps: ["jquery"]
		},
		'front': {
			deps: ["jquery"]
		},
	}
});

require(
	["app"],
	function(App) {
		App.initialize();
	}
);