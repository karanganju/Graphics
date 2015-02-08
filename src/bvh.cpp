#include "bvh.hpp"
#include "error.hpp"
#include "gl_interface.hpp"

using namespace bvh;

//--------------------------------------------------------------------------------
// bvh_t methods

bvh_t::bvh_t(std::string _filename)
{
  hierarchy = NULL;
  motion = NULL;
  has_motion = true;
  bvh_filename = _filename;
  try { read(); }
  catch (util::common::error *e)
    { util::common::error::propogate_error(e); }
}
 
bvh_t::bvh_t(std::string _filename, bool _has_motion)
{
  hierarchy = NULL;
  motion = NULL;
  has_motion = _has_motion;
  bvh_filename = _filename;
  try { read(); }
  catch (util::common::error *e)
    { util::common::error::propogate_error(e); }
}

bvh_t::~bvh_t()
{
  if (hierarchy != NULL) delete hierarchy;
  if (motion != NULL) delete motion;
}

hierarchy_t* bvh_t::get_hierarchy(void)
{
  return hierarchy;
}

motion_t* bvh_t::get_motion(void)
{
  return motion;
}

std::string bvh_t::get_filename(void)
{
  return bvh_filename;
}

bool bvh_t::get_has_motion(void)
{
  return has_motion;
}

void bvh_t::set_hierarchy(hierarchy_t* _hierarchy)
{
  hierarchy = _hierarchy;
}
	
void bvh_t::set_motion(motion_t* _motion)
{
  motion = _motion;
}

void bvh_t::read(void)
{
  if (bvh_filename.empty())
    throw new util::common::warning_error("(bvh_t::read) : Invalid filename");

  std::ifstream inp (bvh_filename.c_str());
  if (inp == NULL)
    throw new util::common::warning_error("(bvh_t::read) : Unable to open file for reading"); 

  hierarchy = new hierarchy_t;

  try { hierarchy->read(inp); }
  catch (util::common::error *e)
    { util::common::error::propogate_error(e); }

  if (has_motion)
    {
      motion = new motion_t;
      motion->set_data_channels(hierarchy->get_tot_num_channels());
      try { motion->read(inp); }
      catch (util::common::error *e)
	{ util::common::error::propogate_error(e); }
    }
  
  inp.close();
}

void bvh_t::print_hierarchy(std::ostream &out)
{
  try 
    { 
      hierarchy->print_lin(out); 
      out<<"Total number of channels : "<<hierarchy->get_tot_num_channels()<<std::endl;
    }
  catch (util::common::error *e)
    { util::common::error::propogate_error(e); }
}

void bvh_t::print_motion(std::ostream &out)
{
  if (has_motion)
    { 
      motion->print(out); 
    }
  else 
    throw new util::common::warning_error("(bvh_t::print_motion) No motion data available");
}

void bvh_t::render_pose(joint_t *jtptr)
{
  //std::cout<<"sdd"<<std::endl;
  double* abspos = new double[3];
  jtptr->get_position(abspos);
  if(jtptr->get_render_mode() == _sphere) {
    double scale = jtptr->get_render_joint_size();
    glScalef(scale,scale,scale);
    GLUquadricObj* quadric = gluNewQuadric();
    gluSphere(quadric,abspos[0],abspos[1],abspos[2]);
    glScalef(1.0/scale,1.0/scale,1.0/scale);
  }
  if(jtptr->get_joint_type() != _root) {
    double* parabspos = new double[3];
    jtptr->get_position(parabspos);
    glLineWidth(2.5); 
    glBegin(GL_LINES);
    glVertex3f(abspos[0],abspos[1],abspos[2]);
    glVertex3f(parabspos[0],parabspos[1],parabspos[2]);
    glEnd();
  }
}

void bvh_t::render_canonical_pose(void)
{
  for(std::list<joint_t *>::iterator iter=(hierarchy->get_joint_list())->begin();iter!=(hierarchy->get_joint_list())->end();iter++){
    joint_t* jtptr = *iter;
    util::math::vec3 posnode = jtptr->get_absolute_offset();
    double abspos[3] = {posnode[0],posnode[1],posnode[2]};
    //hierarchy->update_joint_matrix(jtptr,abspos);
    if(jtptr->get_render_mode() == _sphere) {
      double scale = jtptr->get_render_joint_size();
      glScalef(scale,scale,scale);
      GLUquadricObj* quadric = gluNewQuadric();
      gluSphere(quadric,abspos[0],abspos[1],abspos[2]);
      glScalef(1.0/scale,1.0/scale,1.0/scale);
    }
    if(jtptr->get_joint_type() != _root) {
      util::math::vec3 parposnode = jtptr->get_parent()->get_absolute_offset();
      double parabspos[3] = {parposnode[0],parposnode[1],parposnode[2]};
      glLineWidth(2.5); 
      glBegin(GL_LINES);
      glVertex3f(abspos[0],abspos[1],abspos[2]);
      glVertex3f(parabspos[0],parabspos[1],parabspos[2]);
      glEnd();
    }
  }
}

void bvh_t::render_frame(unsigned int frame_number)
{
  /* CS775: Implement this method */
  //int data_channels = hierarchy->get_tot_num_channels();
  float* data = motion->get_data_row(frame_number);
  std::list<joint_t *>* root = hierarchy->get_joint_list();
  int count =0;
  for (std::list<joint_t *>::iterator it=root->begin();it!=root->end();it++)
  {
    /* code */
    int channels = ((*it)->get_channels()).num_channels;
    //std::cout<<"name is "<<(*it)->get_name()<<" "<<channels<<std::endl;
    float* data_ch = new float();
    //std::cout<<"in mid "<<std::endl;
    for(int i=0;i<channels;i++){
      data_ch[i]=data[count];
      count++;
      //std::cout<<data_ch[i]<<" "<<std::endl;
    }
    double* abspos = new double[3];
    (*it)->get_position(abspos);
    //std::cout<<"before "<<abspos[0]<<" "<<abspos[1]<<" "<<abspos[2]<<std::endl;
    
    hierarchy->update_joint_matrix((*it),data_ch);

    (*it)->get_position(abspos);
    //std::cout<<"after "<<abspos[0]<<" "<<abspos[1]<<" "<<abspos[2]<<std::endl;
    render_pose(*it);
  }
}
