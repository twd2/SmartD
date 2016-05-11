import setuptools

setuptools.setup(name='smartd',
                 version='0.1',
                 author='twd2',
                 author_email='twd2@163.com',
                 description='Smart dormitory.',
                 license='?',
                 keywords='smart dormitory',
                 url='https://pi.twd2.net/',
                 packages=[
                   'smartd',
                   'smartd.view',
                 ],
                 package_data={
                   'smartd': ['template/*'],
                 },
                 install_requires=open('req.txt').readlines())
