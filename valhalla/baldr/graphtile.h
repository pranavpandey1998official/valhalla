#ifndef VALHALLA_BALDR_GRAPHTILE_H_
#define VALHALLA_BALDR_GRAPHTILE_H_

#include <valhalla/baldr/graphid.h>
#include <valhalla/baldr/graphtileheader.h>
#include <valhalla/baldr/directededge.h>
#include <valhalla/baldr/nodeinfo.h>
#include <valhalla/baldr/edgeinfo.h>

namespace valhalla {
namespace baldr {

/**
 * Graph information for a tile within the Tiled Hierarchical Graph.
 * @author  David W. Nesbitt
 */
class GraphTile {
 public:
  /**
   * Constructor
   */
  GraphTile();

  /**
   * Constructor given a GraphId. Reads the graph tile from file
   * into memory.
   */
  GraphTile(const std::string& basedirectory, const GraphId& graphid);

  /**
   * Destructor
   */
  virtual ~GraphTile();

  /**
   * Gets the filename given the graphId
   * @param  graphid  Graph Id to construct filename.
   * @param  basedirectory  Base data directory
   * @return  Returns filename (including directory path relative to tile
   *          base directory
   */
  static std::string Filename(const std::string& basedirectory,
                       const GraphId& graphid);

  /**
   * Gets the directory to a given tile.
   * @param  graphid  Graph Id to construct file directory.
   * @return  Returns file directory path relative to tile base directory
   */
  static std::string FileDirectory(const GraphId& graphid);

  /**
   * Gets the size of the tile in bytes. A value of 0 indicates an empty tile. A value
   * of 0 indicates an error reading the tile data.
   * or unsuccessful read.
   *
   * @return size   the size of the tile in bytes
   */
  size_t size() const;

  /**
   * Gets the id of the graph tile
   *
   * @return id     the graph id of the tile (pointing to the first node)
   */
  GraphId id() const;

  /**
   * Gets a pointer to the graph tile header.
   * @return  Returns the header for the graph tile.
   */
  const GraphTileHeader* header() const;

  /**
   * Get a pointer to a node.
   * @return  Returns a pointer to the node.
   */
  const NodeInfo* node(const GraphId& node) const;

  /**
   * Get a pointer to a node.
   * @param  idx  Index of the node within the current tile.
   * @return  Returns a pointer to the node.
   */
  const NodeInfo* node(const size_t idx) const;

  /**
   * Get a pointer to a edge.
   * @param  edge  GraphId of the directed edge.
   * @return  Returns a pointer to the edge.
   */
  const DirectedEdge* directededge(const GraphId& edge) const;

  /**
   * Get a pointer to a edge.
   * @param  idx  Index of the directed edge within the current tile.
   * @return  Returns a pointer to the edge.
   */
  const DirectedEdge* directededge(const size_t idx) const;

  /**
   * Get a pointer to edge info.
   * @return  Returns edge info.
   */
  EdgeInfo* edgeinfo() const;

 protected:
  // Size of the tile in bytes
  size_t size_;

  // Graph tile memory
  char* graphtile_;

  // Header information for the tile
  GraphTileHeader* header_;

  // List of nodes. This is a fixed size structure so it can be
  // indexed directly.
  NodeInfo* nodes_;

  // List of directed edges. This is a fixed size structure so it can be
  // indexed directly.
  DirectedEdge* directededges_;

  // List of edge info structures. Since edgeinfo is not fixed size we
  // use offsets in directed edges.
  char* edgeinfo_;

  // Street names and exit names/numbers as sets of null-terminated char arrays.
  // Edge info has offsets into this array.
  char* textlist_;

  // The id of the tile for convenience
  const GraphId id_;
};

}
}

#endif  // VALHALLA_BALDR_GRAPHTILE_H_
