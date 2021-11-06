/*	__FILE HEADER__
*	File:		JZMath.cpp
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Custom Math Library.
*/

#include <PCH.h>
#include "JZMath.h"

#include "../DebugTools/Log.h"
#include "../EngineConfig.h"
#include "../EngineGUI/EngineGUI.h"

#include "../DebugTools/PerformanceData.h"

namespace JZEngine
{
	namespace Math
	{
		bool IsEqual(float a, float b)
		{
			return std::abs(a - b) <= EPSILON;
		}

		float Sqr(float a)
		{
			return a * a;
		}

		bool IsEven(int val)
		{
			return val % 2 == 0;
		}

		Mat3f GetModelTransformNonTransposed(const Vec2f& position, float rotate, const Vec2f& scale, const Vec2f& size)
		{
			return (JZEngine::Mat3f::Translate(position.x, position.y) * 
				(JZEngine::Mat3f::RotateZ(Math::DegToRad(rotate)) * JZEngine::Mat3f::Scale(size.x * scale.x, size.y * scale.y, 1.0f)));
		}

		Mat3f GetProjectionTransformNonTransposed()
		{	
			return	{	{2.0f / Settings::camera_width		, 0.0f								, 0.0f},
					{	0.0f								, 2.0f / Settings::camera_height	, 0.0f},
					{	0.0f								, 0.0f								, 1.0f} };
		}

		Mat3f GetTransform( const Vec2f& position, float rotate, const Vec2f& scale, const Vec2f& size )
		{
			PerformanceData::StartMark("Mat3GetTransform (JZMath.cpp|L:20-33)");
			// calculate transformation
			JZEngine::Mat3f mat_scale = JZEngine::Mat3f::Scale( size.x * scale.x, size.y * scale.y, 1.0f );
			JZEngine::Mat3f mat_rotate = JZEngine::Mat3f::RotateZ( Math::DegToRad( rotate ) );
			JZEngine::Mat3f mat_translate = JZEngine::Mat3f::Translate( position.x, position.y );

			/*JZEngine::Mat3f camwin_to_ndc_xform = { {2.0f / ( Settings::aspect_ratio * Settings::window_height ), 0.0f, 0.0f},
													{0.0f, 2.0f / Settings::window_height, 0.0f},
													{0.0f, 0.0f, 1.0f} };*/
			JZEngine::Mat3f camwin_to_ndc_xform = GetProjectionTransformNonTransposed();

			JZEngine::Mat3f transform = mat_translate * ( mat_rotate * mat_scale );
			transform = camwin_to_ndc_xform * EngineGUI::GetCameraTransform() * transform;
			transform.Transpose();
			PerformanceData::EndMark("Mat3GetTransform (JZMath.cpp|L:20-33)");

			return transform;
		}

		void TestMat2(const Mat2d& check, const Mat2d& against)
		{
			double	val{ 1.5 };
			Vec2i	vec2{ 3,2 };
			Mat2d	mat2_0{ check };
			Mat2d	mat2_1{ against };
			Mat2d	mat2_identity;

			Log::Info("Math", "Mat2 Test Cases__________________________________________________");
			Log::Info("Math", "Mat2_0: {}", mat2_0);
			Log::Info("Math", "Mat2_1: {}", mat2_1);
			Log::Info("Math", "Vec2:   {}", vec2);
			Log::Info("Math", "Val:    {}", val);

			Log::Info("Math", "Mat2 Identity:	 {}", mat2_identity);			/*!< result [1.0,0.0], [0.0,1.0] */
			Log::Info("Math", "Mat2_0 +  Mat2_1: {}", mat2_0 + mat2_1);		/*!< result [3.0,3.5], [7.0,7.0] */
			Log::Info("Math", "Mat2_0 -  Mat2_1: {}", mat2_0 - mat2_1);		/*!< result [-1.0,1.5], [-1.0,1.0] */
			Log::Info("Math", "Mat2_0 *  Val:	 {}", mat2_0 * val);			/*!< result [2.0,5.0], [6.0,8.0] */
			Log::Info("Math", "Mat2_0 *  Mat2_1: {}", mat2_0 * mat2_1);		/*!< result [12.0,8.5], [22.0,15.0] */
			Log::Info("Math", "Mat2_0 *  Vec2:   {}", mat2_0 * vec2);		/*!< result [8.0,17.0] */

			Log::Info("Math", "Cast Mat2 to Mat3: {}", static_cast<Mat3d>(mat2_0));
			Log::Info("Math", "Cast Mat2 to Mat4: {}", static_cast<Mat4d>(mat2_0));

			Log::Info("Math", "Cast Mat2d to Mat2<int>: {}", static_cast<Mat2<int>>(mat2_0));

			Log::Info("Math", "Mat2_0 Transpose:	{}", mat2_0.GetTranspose());
			Log::Info("Math", "Mat2_0 Determinant:  {}", mat2_0.Determinant());
			Log::Info("Math", "Mat2_0 Inverse:		{}", mat2_0.GetInverse());
		}

		void TestMat3(const Mat3d& check, const Mat3d& against)
		{
			double val{ 1.5 };
			Vec3i vec3{ 3,2,1 };
			Mat3d mat3_0{ check };
			Mat3d mat3_1{ against };
			Mat3d mat3_identity;

			Log::Info("Math", "Mat3 Test Cases__________________________________________________");
			Log::Info("Math", "Mat3_0: {}", mat3_0);
			Log::Info("Math", "Mat3_1: {}", mat3_1);
			Log::Info("Math", "Vec3:   {}", vec3);
			Log::Info("Math", "Val:    {}", val);

			Log::Info("Math", "Mat3 Identity: {}", mat3_identity);
			Log::Info("Math", "Mat3 +  Mat3: {}", mat3_0 + mat3_1);
			Log::Info("Math", "Mat3 -  Mat3: {}", mat3_0 - mat3_1);
			Log::Info("Math", "Mat3 *  Val: {}", mat3_0 * val);
			Log::Info("Math", "Mat3 *  Mat3: {}", mat3_0 * mat3_1);
			Log::Info("Math", "Mat3 *  Vec3: {}", mat3_0 * vec3);

			Log::Info("Math", "Cast Mat3 to Mat2: {}", static_cast<Mat2d>(mat3_0));
			Log::Info("Math", "Cast Mat3 to Mat4: {}", static_cast<Mat4d>(mat3_0));

			Log::Info("Math", "Cast Mat3d to Mat3<int>: {}", static_cast<Mat3<int>>(mat3_0));

			Log::Info("Math", "Mat3_0 Transpose:	{}", mat3_0.GetTranspose());
			Log::Info("Math", "Mat3_0 Determinant:  {}", mat3_0.Determinant());
			Log::Info("Math", "Mat3_0 Inverse:		{}", mat3_0.GetInverse());
		}

		void TestMat4(const Mat4d& check, const Mat4d& against)
		{
			double val{ 1.5 };
			Vec4i vec4{ 4,3,2,1 };
			Mat4d mat4_0{ check };
			Mat4d mat4_1{ against };
			Mat4d mat4_identity;

			Log::Info("Math", "Mat4 Test Cases__________________________________________________");
			Log::Info("Math", "Mat4_0: {}", mat4_0);
			Log::Info("Math", "Mat4_1: {}", mat4_1);
			Log::Info("Math", "Vec4:   {}", vec4);
			Log::Info("Math", "Val:    {}", val);

			Log::Info("Math", "Mat4 Identity: {}", mat4_identity);
			Log::Info("Math", "Mat4 += Mat4: {}", mat4_0 += mat4_1);
			Log::Info("Math", "Mat4 -= Mat4: {}", mat4_0 -= mat4_1);
			Log::Info("Math", "Mat4 +  Mat4: {}", mat4_0 + mat4_1);
			Log::Info("Math", "Mat4 -  Mat4: {}", mat4_0 - mat4_1);
			Log::Info("Math", "Mat4 *  Mat4: {}", mat4_0 * mat4_1);
			Log::Info("Math", "Mat4 *  Vec4: {}", mat4_0 * vec4);

			Log::Info("Math", "Cast Mat4 to Mat2: {}", static_cast<Mat2d>(mat4_0));
			Log::Info("Math", "Cast Mat4 to Mat3: {}", static_cast<Mat3d>(mat4_0));

			//Log::Info("Math", "Cast Mat2d to Mat2<int>: {}", static_cast<Mat2<int>>(mat2_0));

			Log::Info("Math", "Mat4_0 Transpose:	{}", mat4_0.GetTranspose());
			Log::Info("Math", "Mat4_0 Determinant:  {}", mat4_0.Determinant());
			Log::Info("Math", "Mat4_0 Inverse:		{}", mat4_0.GetInverse());
		}

		void AllMatrixTestCases()
		{
			TestMat2();
			TestMat3();
			TestMat4();
		}
	}
}