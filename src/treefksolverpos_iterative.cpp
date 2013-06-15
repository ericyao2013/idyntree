// Copyright  (C)  2007 Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
// Copyright  (C)  2008 Julia Jesse
// Copyright  (C)  2013 Silvio Traversaro

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include "kdl_codyco/treefksolverpos_iterative.hpp"
#include <iostream>

namespace KDL {
namespace CoDyCo {
    TreeFkSolverPos_iterative::TreeFkSolverPos_iterative(const Tree& tree_arg, const std::string & base_link, TreeSerialization serialization_arg): tree_graph(tree_arg,serialization_arg)
    {
        int ret = tree_graph.DFtraversal(traversal,base_link);
        if( ret != 0 ) {
            tree_graph.DFtraversal(traversal);
        }
    }
    
    TreeFkSolverPos_iterative::~TreeFkSolverPos_iterative()
    {
    }

    int TreeFkSolverPos_iterative::JntToCart(const JntArray& q_in, Frame& p_out, std::string segmentName)
    {
        if( q_in.rows() != tree_graph.getNrOfDOFs() )
            return -1;
            
        LinkMap::const_iterator it;
        it = tree_graph.getLink(segmentName);
        
        if( it == tree_grap.getInvalidLinkIterator() ) 
            return -2;
        
        Frame currentFrame, resultFrame;
        resultFrame = Frame::Identity();
        
        for(LinkMap::const_iterator link=it; link != traversal.order[0]; link = traversal.parent[link->second.link_nr] ) {
            currentFrame = link->second.pose(traversal.parent[link->second.link_nr],
                                             q_in[link->second.getAdjacentJoint(traversal.parent[link->second.link_nr]->second.q_nr]);
            resultFrame = currentFrame*resultFrame;
        }
        
        p_out = result_frame;
        return 0;
    }

    int TreeFkSolverPos_iterative::JntToCart(const JntArray& q_in, Frame& p_out, int segmentIndex)
    {
        if( q_in.rows() != tree_graph.getNrOfDOFs() )
            return -1;
        
        LinkMap::const_iterator 
        /*
		SegmentMap::const_iterator it;
       
        SegmentMap segments;
        segments = tree.getSegments();
                
        if(q_in.rows() != tree.getNrOfJoints() )
    	    	return -1;
        else if( segmentIndex < 0 || segmentIndex > tree.getNrOfSegments() ) //if the segment name is not found
         	return -2;
        else {
            Frame currentFrame, resultFrame;
            resultFrame = Frame::Identity();
            for( int seg = segmentIndex; seg != -1; seg = parent[seg] ) {
                if(index2segment[seg]->second.segment.getJoint().getType() != Joint::None) {
                    currentFrame = index2segment[seg]->second.segment.pose(q_in(link2joint[seg]));
                } else {
                    currentFrame = index2segment[seg]->second.segment.pose(q_in(0));
                }
                resultFrame = currentFrame*resultFrame;
            }
            */
            //p_out = resultFrame;
        return 0;        	
    }
}
    


}
