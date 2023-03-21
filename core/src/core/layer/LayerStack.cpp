#include "_Core.h"
#include "LayerStack.h"


namespace core
{
	LayerStack::LayerStack()
	{
		
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers)
		{
			delete layer;
		}
		layers.clear();
	}

	void LayerStack::AddLayer(Layer* layer)
	{
		layers.emplace(layers.begin() + insertLayerIndex, layer);
		insertLayerIndex++;
	}

	void LayerStack::AddOverlay(Layer* layer)
	{
		layers.emplace_back(layer);
		layer->SetOverlayStatus(true);
	}

	void LayerStack::RemoveLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.begin() + insertLayerIndex, layer);
		if (it != layers.begin() + insertLayerIndex)
		{
			layers.erase(it);
			insertLayerIndex--;
		}
	}

	void LayerStack::RemoveOverlay(Layer* layer)
	{
		auto it = std::find(layers.begin() + insertLayerIndex, layers.end(), layer);
		if (it != layers.end()) 
		{
			layers.erase(it);
		}
	}

	int LayerStack::GetPlace(Layer* layer) const
	{
		stack::const_iterator it = std::find(layers.begin(), layers.end(), layer);
		if (it == layers.end())
			return -1;
		return it - layers.begin();
	}
}
