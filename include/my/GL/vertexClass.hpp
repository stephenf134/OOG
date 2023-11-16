#ifndef _MY_GL_VERTEXCLASS_HPP
#define _MY_GL_VERTEXCLASS_HPP

namespace my
{
	namespace GL
	{
		class vertices
		{
		public:
			class objectClass
			{
			public:
				std::vector<std::vector<float>> triangles;
			private:
				bool solid;
				struct object_gravity_data
				{
					int weight;
					bool has_gravity;
				};
				object_gravity_data gravity_data;

				my::GL::vertices::objectClass insert_triangle(std::pair<float, float> P1, std::pair<float, float> P2, std::pair<float, float> P3)
				{
					// std::cout << "function call to non-static my::GL::vertices::objectClass::insert_triangle(std::pair<float, float>, std::pair<float, float>, std::pair<float, float>, std::pair<float, float>" << std::endl;
					// std::cout << "------------------------------------" << std::endl;
					std::vector<float> new_triangle = std::vector<float>(); /* will have 9 elements (2+1)*3  */
					new_triangle.push_back(P1.first); new_triangle.push_back(P1.second); new_triangle.push_back(1.0f);
					new_triangle.push_back(P2.first); new_triangle.push_back(P2.second); new_triangle.push_back(1.0f);
					new_triangle.push_back(P3.first); new_triangle.push_back(P3.second); new_triangle.push_back(1.0f);
					for (int i = 0; i < new_triangle.size(); i+= 3)
					{
						// std::cout << i / 3 << ": " << new_triangle.at(i) << ", " << new_triangle.at(i + 1) << ", " << new_triangle.at(i + 2) << std::endl;
					}
					triangles.push_back(new_triangle);
					// std::cout << "------------------------------------\n" << std::endl;

					return *this;
				}
			public:

				objectClass()
				{
					solid = false;
					// std::cout << "function call to constructor my::GL::vertices::objectClass::objectClass(void)" << std::endl;
					// std::cout << "------------------------------------" << std::endl;
					triangles = std::vector<std::vector<float>>();
					// std::cout << "triangles = {}" << std::endl;
					// std::cout << "------------------------------------\n" << std::endl;
				}

				static my::GL::vertices::objectClass quad(std::pair<float, float>P1, std::pair<float, float>P2, std::pair<float, float>P3, std::pair<float, float>P4)
				{
					my::GL::vertices::objectClass ret = my::GL::vertices::objectClass();
					ret.insert_triangle(P1, P2, P3);
					ret.insert_triangle(P1, P4, P3);
			
					return ret;
				}

				my::GL::vertices::objectClass translate(float x, float y)
				{
					std::cout << "number of triangles before: " << triangles.size() << std::endl;
					
					for (int i = 0; i < triangles.size(); i++)
					{
					    triangles.at(i).at(0) += x; triangles.at(i).at(1) += y;
					    triangles.at(i).at(3) += x; triangles.at(i).at(4) += y;
					    triangles.at(i).at(6) += x; triangles.at(i).at(7) += y;
					}

					return *this;
				}
			};
			std::vector<objectClass> objects;
			vertices()
			{
				objects = std::vector<objectClass>();
			}

			std::vector<float> float_vec()
			{
				std::vector<float> ret = std::vector<float>();
		
				for (int i = 0; i < objects.size(); i++)
				{
					for (int j = 0; j < objects.at(i).triangles.size(); j++)
					{
						for (int k = 0; k < objects.at(i).triangles.at(j).size(); k++)
						{
							// std::cout << "float_vec pushing back " << objects.at(i).triangles.at(j).at(k) << std::endl;
							ret.push_back(objects.at(i).triangles.at(j).at(k));
						}
					}
				}
				std::cout << "float_vec has " << ret.size() << " floats." << std::endl;
				
				return ret;
			}

			void draw_quad(my::GL::coords P1, my::GL::coords P2, my::GL::coords P3, my::GL::coords P4)
			{
				objects.push_back(objectClass::quad(P1, P2, P3, P4));
			}

			objectClass select_object(int index)
			{
				return objects.at(index);
			}
	
		};
	}
}

#endif
