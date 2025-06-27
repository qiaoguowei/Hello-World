#!/usr/bin/python3

import xml.etree.ElementTree as ET

tree = ET.parse('111.xml')

root = tree.getroot()
'''
for components in root:
    print('Tag: ', components.tag)
    if components.tag == 'components':
        for component in components:
            print('Tag: ', component.tag)
            print('Attributes: ', component.attrib)
            if component.tag == 'component' and component.attrib['name'] == 'ContentAnalyticEngine':
                for feature in component:
                    print('Tag: ', feature.tag)
                    print('Attributes: ', feature.attrib)
                    if feature.tag == 'feature' and feature.attrib['name'] == 'LocalScan':
                        for engines in feature:
                            if engines.tag == 'engines':
                                for engine in engines:
                                    if engine.tag == 'engine' and engine.attrib['name'] == 'AviraLib':
                                        element = engine.find('enabled')
                                        if element.text == 'true':
                                            element.text = 'false'
                                            tree.write('222.xml')
'''

#for ele in root.findall("*/engine[@name='AviraLib']"):
element = root.find("components//component[@name='ContentAnalyticEngine']//feature[@name='LocalScan']//engines//engine[@name='AviraLib']//enabled")

print(element.tag)
print(element.text)
