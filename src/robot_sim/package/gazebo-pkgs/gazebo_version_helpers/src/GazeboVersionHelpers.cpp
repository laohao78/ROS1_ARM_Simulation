
#include <gazebo_version_helpers/GazeboVersionHelpers.h>
#include <gazebo/physics/physics.hh>

namespace gazebo {

GzVector3 GetBoundingBoxDimensions(const ignition::math::v6::AxisAlignedBox &box)
{
  GzVector3 bb(box.XLength(), box.YLength(), box.ZLength());
  return bb;
}

using GzPose3 = gazebo::GzPose3;
using GzVector3 = gazebo::GzVector3;
using GzMatrix3 = gazebo::GzMatrix3;
using GzMatrix4 = gazebo::GzMatrix4;

GzPose3 GetWorldPose(const gazebo::physics::LinkPtr &link)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return link->WorldPose();
#else 
  return link->GetWorldPose();
#endif 
}

GzVector3 GetWorldVelocity(const gazebo::physics::LinkPtr &link)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return link->WorldLinearVel();
#else 
  return link->GetWorldLinearVel();
#endif 
}

GzMatrix4 GetIdentity()
{
#if GAZEBO_MAJOR_VERSION >= 8
  return GzMatrix4::Identity;
#else 
  return GzMatrix4::IDENTITY;
#endif 
}

GzMatrix4 GetMatrix(const GzPose3 &pose)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return GzMatrix4(pose);
#else 
  GzMatrix4 mat = pose.rot.GetAsMatrix4();
  mat.SetTranslate(pose.pos);
  return mat;
#endif 
}

GzMatrix4 GetMatrix(const GzVector3 &pos)
{
  GzMatrix4 mat = GetIdentity();
#if GAZEBO_MAJOR_VERSION >= 8
  mat.SetTranslation(pos);
#else 
  mat.SetTranslate(pos);
#endif 
  return mat;
}

double GetLength(const GzVector3 &v)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return v.Length();
#else 
  return v.GetLength();
#endif 
}

void SetX(GzVector3 &v, const double val)
{
#if GAZEBO_MAJOR_VERSION >= 8
  v.X(val);
#else 
  v.x = val;
#endif 
}

void SetY(GzVector3 &v, const double val)
{
#if GAZEBO_MAJOR_VERSION >= 8
  v.Y(val);
#else 
  v.y = val;
#endif 
}

void SetZ(GzVector3 &v, const double val)
{
#if GAZEBO_MAJOR_VERSION >= 8
  v.Z(val);
#else 
  v.z = val;
#endif 
}

double GetX(const GzVector3 &v)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return v.X();
#else 
  return v.x;
#endif 
}

double GetY(const GzVector3 &v)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return v.Y();
#else 
  return v.y;
#endif 
}

double GetZ(const GzVector3 &v)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return v.Z();
#else 
  return v.z;
#endif 
}

void SetX(GzQuaternion &q, const double val)
{
#if GAZEBO_MAJOR_VERSION >= 8
  q.X(val);
#else 
  q.x = val;
#endif 
}

void SetY(GzQuaternion &q, const double val)
{
#if GAZEBO_MAJOR_VERSION >= 8
  q.Y(val);
#else 
  q.y = val;
#endif 
}

void SetZ(GzQuaternion &q, const double val)
{
#if GAZEBO_MAJOR_VERSION >= 8
  q.Z(val);
#else 
  q.z = val;
#endif 
}

void SetW(GzQuaternion &q, const double val)
{
#if GAZEBO_MAJOR_VERSION >= 8
  q.W(val);
#else 
  q.w = val;
#endif 
}

double GetX(const GzQuaternion &q)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return q.X();
#else 
  return q.x;
#endif 
}

double GetY(const GzQuaternion &q)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return q.Y();
#else 
  return q.y;
#endif 
}

double GetZ(const GzQuaternion &q)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return q.Z();
#else 
  return q.z;
#endif 
}

double GetW(const GzQuaternion &q)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return q.W();
#else 
  return q.w;
#endif 
}

GzVector3 GetVector(const double x, const double y, const double z)
{
#if GAZEBO_MAJOR_VERSION >= 8
  GzVector3 v(x, y, z);
//  v.X(x);
//  v.Y(y);
//  v.Z(z);
#else 
  GzVector3 v;
  v.x = x;
  v.y = y;
  v.z = z;
#endif 
  return v;
}

GzVector3 GetPos(const GzPose3 &pose)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return pose.Pos();
#else 
  return pose.pos;
#endif 
}

GzQuaternion GetRot(const GzPose3 &pose)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return pose.Rot();
#else 
  return pose.rot;
#endif 
}

GzVector3 GetPos(const GzMatrix4 &mat)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return mat.Translation();
#else 
  return mat.GetTranslation();
#endif 
}

GzQuaternion GetRot(const GzMatrix4 &mat)
{
#if GAZEBO_MAJOR_VERSION >= 8
  return mat.Rotation();
#else 
  return mat.GetRotation();
#endif 
}

physics::PhysicsEnginePtr GetPhysics(
  const physics::WorldPtr &world)
{
#if GAZEBO_MAJOR_VERSION >= 8
    return world->Physics();
#else
    return world->GetPhysicsEngine();
#endif
}

physics::EntityPtr GetEntityByName(
  const physics::WorldPtr &world, const std::string &name)
{
#if GAZEBO_MAJOR_VERSION >= 8
    return world->EntityByName(name);
#else
    return world->GetEntity(name);
#endif

}

physics::ModelPtr GetModelByName(
  const physics::WorldPtr &world, const std::string &name)
{
#if GAZEBO_MAJOR_VERSION >= 8
    return world->ModelByName(name);
#else
    return world->GetModel(name);
#endif
}

physics::Model_V GetModels(
  const physics::WorldPtr &world)
{
#if GAZEBO_MAJOR_VERSION >= 8
    return world->Models();
#else
    return world->GetModels();
#endif
}

// 模板实现仍在头文件

} // namespace gazebo
