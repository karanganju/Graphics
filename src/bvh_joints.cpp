#include "bvh_joints.hpp"
#include "error.hpp"
#include "structures.hpp"

using namespace bvh;

//--------------------------------------------------------------------------------
// channel_t methods

channel_t& channel_t::operator = (const channel_t& _ch)
{
  num_channels = _ch.num_channels;
  ch_order[0] = _ch.ch_order[0];
  ch_order[1] = _ch.ch_order[1];
  ch_order[2] = _ch.ch_order[2];
  ch_order[3] = _ch.ch_order[3];
  ch_order[4] = _ch.ch_order[4];
  ch_order[5] = _ch.ch_order[5];

  return *this;
}

//--------------------------------------------------------------------------------
// joint_t methods

joint_t::joint_t()
{
  name = "";
  offset = offset_t(0.0, 0.0, 0.0);
  absolute_offset = offset_t(0.0, 0.0, 0.0);
  parent = NULL;
  render_joint_size = 1.0;
  render_mode = _sphere;
}

joint_t::~joint_t()
{ }

std::string joint_t::get_name(void)
{ 
  return name;
}

int joint_t::get_tname(void)
{ 
  return tname;
}

offset_t joint_t::get_offset(void)
{
  return offset;
}

channel_t joint_t::get_channels(void)
{
  return channels;
}

std::list<joint_t *>* joint_t::get_childlist(void)
{
  return &childlist;
}

joint_types joint_t::get_joint_type(void)
{
  return joint_type;
}

util::math::mat44 joint_t::get_M(void)
{
  return M;
}

offset_t joint_t::get_absolute_offset(void)
{
  return absolute_offset;
}

util::math::mat44 joint_t::get_absolute_M(void)
{
  return absolute_M;
}

joint_t* joint_t::get_parent(void)
{
  return parent;
}

float joint_t::get_render_joint_size(void)
{
  return render_joint_size;
}

joint_render_mode joint_t::get_render_mode(void)
{
  return render_mode;
}

void joint_t::set_name(std::string _name)
{
  name = _name;
}

void joint_t::set_tname(int _name)
{
  tname = _name;
}

void joint_t::set_offset(offset_t _offset)
{
  offset = _offset;
}

void joint_t::set_channels(channel_t _channels)
{
  channels = _channels;
}
	
void joint_t::set_childlist(std::list<joint_t *> _childlist)
{
  childlist = _childlist;
}

void joint_t::set_M(util::math::mat44 _M)
{
  M = _M;
}

void joint_t::set_joint_type(joint_types _joint_type)
{
  joint_type = _joint_type;
}

void joint_t::set_absolute_offset(offset_t _absolute_offset)
{
  absolute_offset = _absolute_offset;
}

void joint_t::set_absolute_M(util::math::mat44 _absolute_M)
{
  absolute_M = _absolute_M;
}

void joint_t::set_parent(joint_t* _parent)
{
  parent = _parent;
}

void joint_t::set_render_joint_size(float _render_joint_size)
{
  render_joint_size = _render_joint_size;
}

void joint_t::set_render_mode(joint_render_mode _render_mode)
{
  render_mode = _render_mode;
}

void joint_t::read(std::ifstream &inp, std::string strtoken)
{
  if (token_map_array::get_token(strtoken) == _ROOT)
    {
      joint_type = _root;
    }
  else if (token_map_array::get_token(strtoken) == _JOINT)
    {
      joint_type = _joint;
    }
  else if (strtoken == "End")
    {
      std::string temptoken;
      inp>>temptoken;
      if (token_map_array::get_token(strtoken+" "+temptoken) == _ENDSITE)
	{
	  joint_type = _endsite;
	}
    }
  else
    throw new util::common::warning_error("(bvh::read) : Missing 'ROOT/JOINT/End Site' tag in bvh file");
  
  if (joint_type != _endsite) inp>>name;
  else if(parent->name == "LeftHand" || parent->name == "RightHand") tname= connect;

  if(name == "ToSpine") tname = bust;
  else if (name == "Hips")  tname = pelvis;
  else if (name == "Neck")  tname = neck;
  else if (name == "Head")  tname = head;
  else if (name == "LeftArm")  tname = arm;
  else if (name == "RightArm") tname = arm;
  else if (name == "LeftForeArm") tname = forearm;
  else if (name == "RightForeArm") tname = forearm;
  else if (name == "LeftHand") tname = hand;
  else if (name == "RightHand") tname = hand;
  else if (name == "LeftUpLeg") tname = thighs;
  else if (name == "RightUpLeg") tname = thighs;
  else if (name == "LeftFoot") tname = foot;
  else if (name == "RightFoot") tname = foot;
  else if (name == "LeftLeg") tname = leg;
  else if (name == "RightLeg") tname = leg;
  else tname = -1;
  inp>>strtoken;

  if (token_map_array::get_token(strtoken) != _CURLY_BRACE_OPEN)
    throw new util::common::warning_error("(bvh::read) : Missing '{' in bvh file");

  inp>>strtoken;

  if (token_map_array::get_token(strtoken) != _OFFSET)
    throw new util::common::warning_error("(bvh::read) : Missing 'OFFSET' tag in bvh file");

  inp>>offset[util::math::X]>>offset[util::math::Y]>>offset[util::math::Z];

  if (joint_type == _root) absolute_offset = offset;

  if (joint_type != _endsite)
    {
      inp>>strtoken;
      if (token_map_array::get_token(strtoken) != _CHANNELS)
	throw new util::common::warning_error("(bvh::read) : Missing 'CHANNELS' tag in bvh file");
      
      inp>>channels.num_channels;

      for(int i = 0; i < channels.num_channels; i++)
	{
	  inp>>strtoken;
	  switch (token_map_array::get_token(strtoken))
	    {
	    case _XPOS: channels.ch_order[i] = _xpos; break;
	    case _YPOS: channels.ch_order[i] = _ypos; break;
	    case _ZPOS: channels.ch_order[i] = _zpos; break;
	    case _XROT: channels.ch_order[i] = _xrot; break;
	    case _YROT: channels.ch_order[i] = _yrot; break;
	    case _ZROT: channels.ch_order[i] = _zrot; break;
	    default: 
	      throw new util::common::warning_error("(bvh::read) : Incorrect channel specification in bvh file");
	    }
	}
    }

  inp>>strtoken;
  while (token_map_array::get_token(strtoken) != _CURLY_BRACE_CLOSE)
    {
      joint_t* newchild = new joint_t;
      try
	{
    newchild->parent = this;
	  newchild->read(inp, strtoken);
	}
      catch (util::common::error *e)
	{
	  util::common::error::propogate_error(e);
	}
      childlist.push_back(newchild);
      inp>>strtoken;
    }
}

void joint_t::print(std::ostream &out)
{
  std::string strjttype;
  (joint_type == _root)? strjttype = std::string("ROOT") : ((joint_type == _joint)? strjttype = std::string("JOINT") : strjttype = std::string("END SITE"));

  out<<"Joint Name : "<<name<<std::endl;
  out<<"Joint Type : "<<strjttype<<std::endl;
  out<<"Joint Offset : <"<<offset[util::math::X]<<","<<offset[util::math::Y]<<","<<offset[util::math::Z]<<">"<<std::endl;
  out<<"Joint Absolute Offset : <"<<absolute_offset[util::math::X]<<","<<absolute_offset[util::math::Y]<<","<<absolute_offset[util::math::Z]<<">"<<std::endl;
  if (joint_type != _endsite)
    {
      out<<"Number of channels : "<<channels.num_channels<<std::endl;
      out<<"Channel Order : ";
      for(int i = 0; i < channels.num_channels; i++)
	out<<channels.ch_order[i]<<" ";
      out<<std::endl;
    }
  out<<std::endl;
  out.flush();
}

void joint_t::update_matrix(float *data_channels)
{
  /* CS775: Implement this method. */
  util::math::vec3 off = offset; 
  double tx=offset[0],ty=offset[1],tz=offset[2];
  util::math::mat44 r[3];
  r[0] = util::math::mat44::identity3D();
  r[1] = util::math::mat44::identity3D();
  r[2] = util::math::mat44::identity3D();
  int count=0;
  util::math::vec3 xax=util::math::vec3(1,0,0),yax=util::math::vec3(0,1,0),zax=util::math::vec3(0,0,1);

  for(int i = 0; i < channels.num_channels; i++){
    switch (channels.ch_order[i])
    {
      case _xpos: tx=data_channels[i]; break;
      case _ypos: ty=data_channels[i]; break;
      case _zpos: tz=data_channels[i]; break;
      case _xrot: r[count]=util::math::mat44::rotation3D(xax,data_channels[i]); count++; break;
      case _yrot: r[count]=util::math::mat44::rotation3D(yax,data_channels[i]); count++; break;
      case _zrot: r[count]=util::math::mat44::rotation3D(zax,data_channels[i]); count++; break;
    }
  }
  util::math::mat44 translation = util::math::mat44::translation3D(tx,ty,tz);
  util::math::mat44 rotation = r[1]*r[2];
  rotation = r[0]*rotation;
  M = translation*rotation;
}

void joint_t::get_position(double* position){
  position[0]=absolute_M[util::math::X][util::math::W];
  position[1]=absolute_M[util::math::Y][util::math::W];
  position[2]=absolute_M[util::math::Z][util::math::W];
}
