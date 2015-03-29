define([ "backbone", "underscore", "models/widgetCollection", "models/widgetGet", "models/widgetSet" ],
function(Backbone, _, WidgetCollection, WidgetGet, WidgetSet) {
	var Widget = Backbone.View.extend({
		el : $("body"),
		initialize : function(options) {
			_.bindAll(this, 'render', 'addItem');
			_.bindAll(this, 'render', 'commut');
			
			this.widgetCollection = new WidgetCollection;
			this.dataRest = false;
			var that = this;
			this.widgetCollection.fetch({
		        complete: function (datas) {
		        	that.dataRest = datas;
		        	that.renderListe();
		        }
		    });
		},
		
		events: {
	      'click button#addWidget': 'addItem',
	      'click button#commut': 'commut'
	    },
	    
	    template: _.template($('#widgetCollectionTemplate').html()),

	    renderListe: function() {
	    	$('#select-content', this.el).html(this.template({ "widgets": this.dataRest.responseJSON}));
	    },
	    
	    addItem: function(){
	    	var selectValue = $('#select-content', this.el).find("select#connectedObject").val();
			if (selectValue == "") {
				alert('Choose an object');
				return false;
			}
			var widgets = this.dataRest.responseJSON;
			this.widgetGet = new WidgetGet([], {famille: this.dataRest.responseJSON[selectValue].famille, key: selectValue});
			this.widgetValue = false;
			var that = this;
			this.widgetGet.fetch({
		        complete: function (datas) {
		        	that.widgetValue = datas;
		        	that.renderAddItem(widgets, selectValue, datas.responseJSON);
		        }
		    });
        },	
        renderAddItem: function(widgets, selectValue, widgetValue) {
        	var templateAddWidget = _.template($('#Widget').html())
        	
        	$('#content', this.el).append(templateAddWidget({ "widget": widgets[selectValue], "widgetValue": widgetValue}));
        },
	    
        commut: function() {
        	this.widgetSet = new WidgetSet([], {key: 'prise4', commut: 1});
        	this.widgetSet.fetch({
		        complete: function (datas) {
		        	alert('c good');
		        }
		    });
        }
	});
	return Widget;
});